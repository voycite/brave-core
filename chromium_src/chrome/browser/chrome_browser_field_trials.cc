/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/chrome_browser_field_trials.h"

#include "build/build_config.h"
#include "components/variations/feature_overrides.h"

#if BUILDFLAG(IS_ANDROID)
#include "base/android/device_info.h"
#endif

#define ChromeBrowserFieldTrials ChromeBrowserFieldTrialsChromium

#include <chrome/browser/chrome_browser_field_trials.cc>

#undef ChromeBrowserFieldTrials

void ChromeBrowserFieldTrials::SetUpClientSideFieldTrials(
    bool has_seed,
    const variations::EntropyProviders& entropy_providers,
    base::FeatureList* feature_list) {
  // Don't setup upstream's client-side field trials.
}

void ChromeBrowserFieldTrials::RegisterFeatureOverrides(
    base::FeatureList* feature_list) {
#if BUILDFLAG(IS_ANDROID)
  if (base::android::device_info::is_desktop()) {
    // Google-only features from upstream's desktop Android overrides. The
    // first override registered for a feature wins, so these must be
    // registered before upstream's.
    variations::FeatureOverrides feature_overrides(*feature_list);
    feature_overrides.DisableFeature(features::kGlic);
    feature_overrides.DisableFeature(features::kGlicActor);
    feature_overrides.DisableFeature(features::kGlicAndroidSidePanel);
    feature_overrides.DisableFeature(features::kGlicRollout);
    feature_overrides.DisableFeature(glic::kContextualCueing);
    feature_overrides.DisableFeature(chrome::android::kEnableAndroidSidePanel);
    feature_overrides.DisableFeature(chrome::android::kAndroidFreLayoutUpdate);
    feature_overrides.DisableFeature(chrome::android::kAccountPickerDialog);
    feature_overrides.DisableFeature(
        chrome::android::kAuxiliarySearchHistoryDonation);
  }
#endif  // BUILDFLAG(IS_ANDROID)
  ChromeBrowserFieldTrialsChromium::RegisterFeatureOverrides(feature_list);
}
